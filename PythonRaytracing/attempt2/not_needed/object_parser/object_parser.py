# adapted from https://github.com/kohterai/OBJ-Parser/blob/master/objParser.py

def parse_obj(obj_file_path, final_texture_path=None, final_vertex_path=None):
	
	obj_file = open('pear.obj', 'r')
	final_texture = open('finalTexture.txt', 'w')
	final_vertex = open('finalVertex.txt', 'w')

	vertex_list = []
	texture_list = []

	final_vertex_list = []
	final_texture_list = []

	for line in obj_file:
		split = line.split()
		# if blank line, skip
		if not len(split):
			continue
		if split[0] == "v":
			vertex_list.append(split[1:])
		elif split[0] == "vt":
			texture_list.append(split[1:])
		elif split[0] == "f":
			count = 1
			first_set = []
			second_set = []
			first_texture_set = []
			second_texture_set = []
			while count < 5:
				remove_slash = split[count].split('/')
				if count == 1:
					first_set.append(vertex_list[int(remove_slash[0]) - 1])
					second_set.append(vertex_list[int(remove_slash[0]) - 1])
					first_texture_set.append(texture_list[int(remove_slash[1]) - 1])
					second_texture_set.append(texture_list[int(remove_slash[1]) - 1])
				elif count == 2:
					first_set.append(vertex_list[int(remove_slash[0]) - 1])
					first_texture_set.append(texture_list[int(remove_slash[1]) - 1])
				elif count == 3:
					first_set.append(vertex_list[int(remove_slash[0]) - 1])
					second_set.append(vertex_list[int(remove_slash[0]) - 1])
					first_texture_set.append(texture_list[int(remove_slash[1]) - 1])
					second_texture_set.append(texture_list[int(remove_slash[1]) - 1])
				elif count == 4:
					second_set.append(vertex_list[int(remove_slash[0]) - 1])
					second_texture_set.append(texture_list[int(remove_slash[1]) - 1])

				count += 1
			final_vertex_list.append(first_set)
			final_vertex_list.append(second_set)
			final_texture_list.append(first_texture_set)
			final_texture_list.append(second_texture_set)

	vertex_count = 0
	for item in final_vertex_list:
		for coordinate_trio in item:
			for coordinate in coordinate_trio:
				final_vertex.write(str(coordinate) + 'f*x, ')
		vertex_count += 1

	texture_count = 0
	for item in final_texture_list:
		for coordinate_trio in item:
			for coordinate in coordinate_trio:
				final_texture.write(str(coordinate) + 'f, ')
		texture_count += 1

	print("Total vertices: " + str(vertex_count * 3))
	print("Total texture cordinates: " + str(vertex_count * 2))

	obj_file.close()
	final_texture.close()
	final_vertex.close()
